#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

// 정점(Vertex)의 타입을 구분하기 위한 열거형
enum class NodeType { USER, MOVIE };

// 그래프의 정점(Vertex) 구조체: 이름, 타입, 상세정보(장르) 저장
struct Node { std::string name; NodeType type; std::string details; };

// 그래프 자료구조 및 추천 알고리즘 관리 클래스
class RecommendationGraph {
private:
    // 인접 리스트(Adjacency List): [출발 정점 ID] -> 목록([도착 정점 ID, 평점 가중치])
    std::map<std::string, std::vector<std::pair<std::string, int>>> adj;
    // 정점 데이터 저장 맵: [정점 ID] -> 정점 구조체
    std::map<std::string, Node> nodes;

public:
    // 그래프에 새로운 정점(유저 또는 영화) 추가
    void addNode(std::string id, std::string name, NodeType t, std::string d) { nodes[id] = {name, t, d}; }
    
    // 그래프에 무방향 간선(Edge) 및 평점(Weight) 추가
    void addEdge(std::string u, std::string m, int r) { adj[u].push_back({m, r}); adj[m].push_back({u, r}); }
    
    // 특정 ID의 정점 정보 반환
    Node getNode(std::string id) { return nodes[id]; }
    
    // 특정 유저가 시청한 영화 간선 목록 반환
    std::vector<std::pair<std::string, int>> getWatched(std::string u) { return adj[u]; }

    // [핵심 알고리즘] 2Hop~3Hop 이웃 탐색 기반 소셜 필터링 추천
    std::vector<std::string> getRec(std::string target) {
        std::set<std::string> myWatched;
        // 1. 타겟 유저가 이미 본 영화들을 검색하여 중복 제거 셋에 저장
        for (auto& e : adj[target]) myWatched.insert(e.first);
        
        std::map<std::string, int> cand; // 추천 후보 영화들의 [ID -> 누적 평점점수]
        
        // 2. 그래프 탐색: 내가 본 영화(1Hop) -> 그 영화를 본 다른 유저(2Hop) -> 그 유저가 본 다른 영화(3Hop)
        for (auto& m : myWatched) {
            for (auto& uEdge : adj[m]) {
                if (uEdge.first == target) continue; // 나 자신은 타인에서 제외
                
                for (auto& mEdge : adj[uEdge.first]) {
                    // 내가 아직 보지 않은 영화들만 추천 후보 정점으로 등록하고 평점 누적
                    if (myWatched.find(mEdge.first) == myWatched.end()) cand[mEdge.first] += mEdge.second;
                }
            }
        }
        // 3. 추천 점수가 높은 순으로 정렬하기 위해 벡터로 복사 후 정렬 수행
        std::vector<std::pair<std::string, int>> sorted(cand.begin(), cand.end());
        std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
        
        // 4. 정렬된 결과 중 상위 3개의 영화 정점 ID만 결과 벡터에 담아 반환
        std::vector<std::string> res;
        for (size_t i = 0; i < sorted.size() && i < 3; ++i) res.push_back(sorted[i].first);
        return res;
    }
};

// Qt GUI 메인 윈도우 클래스 (화면 설계 및 이벤트 처리)
class MainWindow : public QMainWindow {
private:
    RecommendationGraph graph; // 내부 그래프 데이터 객체
    std::string curUser = "";   // 현재 UI에서 선택된 유저 ID
    QLabel *infoLabel;
    QListWidget *userList, *detailList;
    QPushButton *recButton;

    // 프로그램 실행 시 서버 대신 그래프에 하드코딩 데이터를 주입하는 함수
    void initData() {
        graph.addNode("u1", "김찬호", NodeType::USER, "액션/SF");
        graph.addNode("u2", "장지환", NodeType::USER, "로맨스/드라마");
        graph.addNode("u3", "손인욱", NodeType::USER, "액션/스릴러");
        graph.addNode("m1", "인셉션", NodeType::MOVIE, "SF");
        graph.addNode("m2", "어벤져스", NodeType::MOVIE, "액션");
        graph.addNode("m3", "라라랜드", NodeType::MOVIE, "로맨스");
        graph.addNode("m4", "기생충", NodeType::MOVIE, "스릴러");
        graph.addNode("m5", "인터스텔라", NodeType::MOVIE, "SF");
        graph.addEdge("u1", "m1", 5); graph.addEdge("u1", "m2", 4);
        graph.addEdge("u2", "m3", 5); graph.addEdge("u2", "m4", 4);
        graph.addEdge("u3", "m2", 5); graph.addEdge("u3", "m5", 4);
    }
public:
    MainWindow() {
        setWindowTitle("자료구조 OTT 추천"); resize(600, 400); initData();
        
        // 레이아웃 설정을 위한 메인 센트럴 위젯 생성
        QWidget* central = new QWidget(this); setCentralWidget(central);
        QHBoxLayout* mainLayout = new QHBoxLayout(central);
        
        // 좌측 영역: 유저 목록 화면 구성
        QVBoxLayout* left = new QVBoxLayout();
        userList = new QListWidget();
        userList->addItem("User1 (김찬호)"); userList->addItem("User2 (장지환)"); userList->addItem("User3 (손인욱)");
        left->addWidget(new QLabel("<h3>유저 목록</h3>")); left->addWidget(userList);
        
        // 우측 영역: 상세 기록 및 추천 피드백 화면 구성
        QVBoxLayout* right = new QVBoxLayout();
        infoLabel = new QLabel("<h3>유저를 선택하세요.</h3>");
        detailList = new QListWidget();
        recButton = new QPushButton("콘텐츠 추천받기"); recButton->setEnabled(false); // 선택 전까지 버튼 비활성화
        right->addWidget(infoLabel); right->addWidget(detailList); right->addWidget(recButton);
        
        // 메인 레이아웃에 좌우 비율을 1:2로 배치
        mainLayout->addLayout(left, 1); mainLayout->addLayout(right, 2);

        // [시그널-슬롯 연결 1] 유저 목록에서 항목을 클릭(선택)했을 때의 이벤트 처리
        connect(userList, &QListWidget::currentTextChanged, this, [this](const QString& txt) {
            if (txt.startsWith("User1")) curUser = "u1";
            else if (txt.startsWith("User2")) curUser = "u2";
            else if (txt.startsWith("User3")) curUser = "u3";
            
            // 그래프에서 선택된 유저 정보를 찾아 상단 라벨 텍스트 변경
            Node uNode = graph.getNode(curUser);
            infoLabel->setText(QString("<h3>%1 선호: %2</h3>").arg(QString::fromStdString(uNode.name)).arg(QString::fromStdString(uNode.details)));
            
            // 유저의 과거 시청 목록(연결된 영화 정점들)을 그래프에서 조회하여 우측 리스트 위젯에 출력
            detailList->clear();
            for (auto& item : graph.getWatched(curUser)) {
                Node m = graph.getNode(item.first);
                detailList->addItem(QString("- %1 (%2점) [%3]").arg(QString::fromStdString(m.name)).arg(item.second).arg(QString::fromStdString(m.details)));
            }
            recButton->setEnabled(true); // 유저가 선택되었으므로 추천 버튼 활성화
        });

        // [시그널-슬롯 연결 2] 추천받기 버튼을 클릭했을 때 알림창 팝업 이벤트 처리
        connect(recButton, &QPushButton::clicked, this, [this]() {
            QString msg = "★ 추천 리스트 ★\n\n";
            auto recs = graph.getRec(curUser); // 그래프 알고리즘 함수 호출
            if (recs.empty()) msg += "새로운 추천이 없습니다.";
            else {
                int r = 1;
                for (const auto& id : recs) {
                    Node m = graph.getNode(id);
                    msg += QString("%1. %2 (%3)\n").arg(r++).arg(QString::fromStdString(m.name)).arg(QString::fromStdString(m.details));
                }
            }
            // QMessageBox 알림창을 통해 사용자 피드백 제공 (교수님 예시 요구사항)
            QMessageBox::information(this, "추천 완료", msg);
        });
    }
};

// 프로그램 진입점
int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // Qt 어플리케이션 초기화
    MainWindow w; w.show();        // 메인 윈도우 객체 생성 및 시각화
    return app.exec();             // 이벤트 루프 시작
}