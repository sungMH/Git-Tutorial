#include <bangtal.h>//Scene.h 포함
#include <Windows.h>
using namespace bangtal;


int main()
{
	// 1. 장면 생성.
	auto scene0 = Scene::create("게임 시작 화면", "images/게임시작.png");
	ScenePtr scene1 = Scene::create("룸1", "images/배경-1.png");
	//auto scene1 = Scene::create("룸1", "images/배경-1.png");
	auto scene2 = Scene::create("룸2", "images/배경-2.png");
	auto scene3 = Scene::create("룸3_갇힌 방", "images/배경-3.png");
	auto sceneBoom = Scene::create("폭발!", "images/폭발배경.png");
	auto scene4 = Scene::create("탈출", "images/탈출.png");
	
	auto startButton = Object::create("images/start.png", scene0, 790, 470);
	auto endButton1 = Object::create("images/end.png",scene0,790,350);
	auto endButton2 = Object::create("images/end.png", sceneBoom, 590, 350);
	auto endButton3 = Object::create("images/end.png", scene4, 590, 350);

	auto timer = Timer::create(15.0f);//방2에 사용할 타이머

	scene0->setOnEnterCallback([&](ScenePtr sp)->bool {
		timer->set(15.0f);
		hideTimer();
		showMessage("방탈출 게임에 오신 것을 환영합니다!");
			return true;
		});

	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		scene1->enter();
		return true;
		});



	endButton1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		endGame();
		return true;
		});

	endButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		endGame();
		return true;
		});
	endButton3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		endGame();
		return true;
		});

	

	timer->setOnTimerCallback([&](TimerPtr)->bool {

		showMessage("폭발!!!!!");
		sceneBoom->enter();//폭발 배경으로 바꿈
		return true;
	});

	
	
	auto boom = Object::create("images/폭탄.png", scene2, 700, 150);
	boom->setScale(0.1f);
	boom->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		showMessage("폭탄의 타이머가 작동되고 있어! 빨리 탈출해야 겠어!");
		return true;
	});



	//6. 열쇠를 만든다
	auto key = Object::create("images/열쇠.png", scene1, 600, 150);
	key->setScale(0.2f);//비율 조정

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		key->pick();
		return true;
		});

	auto flowerpot_moved = false; //다시 움직이지 않도록 움직였는지 상태저장
	auto flowerpot = Object::create("images/화분.png", scene1, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		if (flowerpot_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 450, 150);
				flowerpot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 650, 150);
				flowerpot_moved = true;
			}
		}
		return true;
		});

	auto flowerpot_moved2 = false; //다시 움직이지 않도록 움직였는지 상태저장
	auto flowerpot2 = Object::create("images/화분.png", scene1, 250, 150);
	flowerpot2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		if (flowerpot_moved2 == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot2->locate(scene1, 150, 150);
				flowerpot_moved2 = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot2->locate(scene1, 350, 150);
				flowerpot_moved2 = true;
			}
		}
		return true;
		});

	// 3. 문을 생성한다.
	auto open1 = false;
	auto door1 = Object::create("images/문-오른쪽-닫힘.png", scene1, 800, 270);

	//4.문을 클릭하면 이동한다.
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function

		//5. 문이 열린 상태이면 게임을 종료한다.
		//   문이 닫힌 상태이면 문을 열어준다.
		if (open1 == true) {
			scene2->enter();//장면2로 전환한다.
			showTimer(timer); 
			showMessage("째깍 째깍... 뭐야! 폭탄의 타이머가 15초밖에 안남았잖아!!!");
			timer->start();
		}
		else if (key->isHanded()) {//키가 손에 있으면
			door1->setImage("images/문-오른쪽-열림.png");
			open1 = true;
		}
		else {
			showMessage("열쇠가 필요해!!!");
		}

		return true;
		});
	//door1->setOnMouseCallback(door1_mouseCallback);

	auto door2 = Object::create("images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		scene1->enter();
		return true;
		});

	auto open3 = false, locked3 = true;
	auto door3 = Object::create("images/문-오른쪽-닫힘.png", scene2, 900, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
	//5. 문이 열린 상태이면 게임을 종료한다.
	//   문이 닫힌 상태이면 문을 열어준다.
		if (locked3) {
			showMessage("문이 잠겨있다.");
		}
		else if (open3 == true) {
			timer->stop();
			hideTimer();
			scene3->enter();
			showMessage("끼잉 쾅!, 문이 닫혔군... 꼼짝없이 갇혀버렸어...");
		}
		else {
			door3->setImage("images/문-오른쪽-열림.png");
			open3 = true;
		}
		return true;
		});



	auto keypad = Object::create("images/키패드.png", scene2, 885, 420);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("77777", door3);//키패드암호, 키패드암호를 성공했을 때 이벤트를 수신할 곳
		return true;
		});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		//키패드 암호 성공해서 door3가 그 신호를 받았을경우 keypadCallBack이 전해짐
		showMessage("철커덕--------");
		locked3 = false;
		keypad->hide();
		return true;
		});

	auto password = Object::create("images/화분밑.png", scene2, 400, 100, false);//보이지 않는 상태로 패스워드 생성

	auto lighted = true;
	auto button = Object::create("images/스위치.png", scene2, 880, 440);
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) {//켜진 상태
			scene2->setLight(0.2f);
			password->show();
			lighted = false;
		}
		else {//꺼진 상태
			scene2->setLight(1.0f);
			password->hide();
			lighted = true;
		}
		return true;
		});

	auto num = Object::create("images/화분밑숫자.png", scene2, 300, 150);
	num->setScale(0.2f);//비율 조정

	auto flowerpot_moved3 = false; //다시 움직이지 않도록 움직였는지 상태저장
	auto flowerpot3 = Object::create("images/화분.png", scene2, 250, 150);
	flowerpot3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		if (flowerpot_moved3 == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot3->locate(scene2, 150, 150);
				flowerpot_moved3 = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot3->locate(scene2, 350, 150);
				flowerpot_moved3 = true;
			}
		}
		return true;
		});

	num->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		num->pick();
		return true;
		});
	
	

	auto hidden_door = Object::create("images/문-오른쪽-닫힘.png", scene3, 370, 400, false);
	hidden_door->setScale(0.8f);

	auto vending_machine = Object::create("images/자판기.png", scene3, 370, 370);
	auto hint1 = Object::create("images/금고속종이.png", scene3, 10, 10, false);



	auto flag = Object::create("images/표지판.png", scene3, 150, 500);
	flag->setScale(0.2f);//비율 조정

	vending_machine->setScale(1.0f);//비율 조정


	auto box = Object::create("images/금고.png", scene3, 670, 270);
	box->setScale(0.2f);//비율 조정


	auto password2 = Object::create("images/힌트2.png", scene3, 400, 100, false);//보이지 않는 상태로 패스워드 생성

	auto box_locked = true;




	auto keypad2 = Object::create("images/키패드2.png", scene3, 670, 270);
	keypad2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("33333", box);//키패드암호, 키패드암호를 성공했을 때 이벤트를 수신할 곳
		return true;
		});

	box->setOnKeypadCallback([&](ObjectPtr object)->bool {

		showMessage("철커덕--------");
		box_locked = false;
		return true;
		});

	box->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function
		if (box_locked) {
			showMessage("금고를 열려면 비밀 번호가 필요하겠어.");
		}
		else {//열린상태
			hint1->pick();
		}
		return true;
		});


	auto lighted2 = true;
	auto button2 = Object::create("images/스위치.png", scene3, 650, 540);
	button2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted2) {//켜진 상태
			scene3->setLight(0.2f);
			password2->show();
			lighted2 = false;
		}
		else {//꺼진 상태
			scene3->setLight(1.0f);
			password2->hide();
			lighted2 = true;
		}
		return true;
		});


	auto keypad3 = Object::create("images/키패드3.png", scene3, 370, 470);
	keypad3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("46810", vending_machine);//키패드암호, 키패드암호를 성공했을 때 이벤트를 수신할 곳
		return true;
		});

	keypad3->setScale(2.0f);//비율 조정

	vending_machine->setOnKeypadCallback([&](ObjectPtr object)->bool {

		showMessage("지지이이이이잉--------, 어! 자판기가 이동한다!");
		vending_machine->locate(scene3, 470, 370);
		keypad3->locate(scene3, 470, 470);
		hidden_door->show();
		return true;
		});

	auto opened = false;
	hidden_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//lambda function

		//5. 문이 열린 상태이면 게임을 종료한다.
		//   문이 닫힌 상태이면 문을 열어준다.
		if (opened == true) {
			scene4->enter();
			showMessage("탈출 성공!!");
		}
		else {
			hidden_door->setImage("images/문-오른쪽-열림.png");
			showMessage("문이 열렸습니다!!!");
			opened = true;
		}

		return true;
		});




	// 2. 게임을 시작한다.
	startGame(scene0);

	return 0;
}