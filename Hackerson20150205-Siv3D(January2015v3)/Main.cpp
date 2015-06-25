# include <Siv3D.hpp>
#include"MREntityManager.hpp"
#include"MRVehicle.hpp"

struct Schedule
{
	Schedule(){}

	Schedule(unsigned int t, MREnemy* p) :term(t), enemy(p)
	{}

	std::shared_ptr<MREnemy> enemy;

	unsigned int term;
};

void Main()
{
	const Font font(30);

	std::vector<Schedule> wave;

	size_t waveIndex = 0;
	
	wave.push_back(Schedule(2000, new MREnemyRound({ 30, 120 }, { 5, 0 }, 2)));
	wave.push_back(Schedule(0, new MREnemyRound({ 610, 360 }, { -5, 0 }, 2)));

	for (int i = 0; i < 2; ++i)
	{
		wave.push_back(Schedule(200, new MREnemyRound({ 30, 120 }, { 5, 0 }, 2)));
		wave.push_back(Schedule(0, new MREnemyRound({ 610, 360 }, { -5, 0 }, 2)));
	}

	wave.push_back(Schedule(5000, new MREnemyStop({ 550, 400 }, 12)));
	wave.push_back(Schedule(0, new MREnemyStop({ 110, 400 }, 12)));
	wave.push_back(Schedule(0, new MREnemyStop({ 550, 80 }, 12)));
	wave.push_back(Schedule(0, new MREnemyStop({ 110, 80 }, 12)));

	wave.push_back(Schedule(12000, new MREnemyRound({ 630, 60 }, { -10, 3 })));
	wave.push_back(Schedule(0, new MREnemyRound({ 30, 60 }, { 10, 3 })));

	for (int i = 0; i < 30; ++i)
	{
		wave.push_back(Schedule(300, new MREnemyRound({ 630, 60 }, { -10, 3 })));
		wave.push_back(Schedule(0, new MREnemyRound({ 30, 60 }, { 10, 3 })));
	}

	Graphics::SetBackground(Palette::Skyblue);

	TextureAsset::Register(L"mame", L"Resource/mame.png");
	TextureAsset::Register(L"ballet1", L"Resource/mame1.png");
	TextureAsset::Register(L"ballet3", L"Resource/daizu.png");
	TextureAsset::Register(L"ballet2", L"Resource/hiyokomame.png");
	TextureAsset::Register(L"back", L"Resource/back.png");
	TextureAsset::Register(L"player", L"Resource/player.png");
	TextureAsset::Register(L"oni", L"Resource/oni.png");

	FontAsset::Register(L"Score", 32, L"Georgia");
	FontAsset::Register(L"Result", 16, L"ＭＳ 明朝");
	MRVehicle myVehicle;

	TimerMillisec timer;

	int scene = 0;//temp

	int result = 0;//temp

	while (System::Update())
	{
		TextureAsset(L"back").draw();
		myVehicle.draw();
		MREntityManager::GetInstance()->draw();

		/*tempのシーン管理*/
		switch (scene)
		{
		case 0:
			FontAsset(L"Result").drawCenter(L"Click to Start", Point(320, 300), Palette::Red);
			if (Input::MouseL.clicked)
			{
				scene = 1;
				timer.start();
			};
			break;
		case 1:
			myVehicle.update();
			MREntityManager::GetInstance()->update();
			if (wave.size() <= waveIndex)
			{
				scene = 2;
				timer.restart();
				continue;
			}

			if (wave[waveIndex].term < timer.elapsed())
			{
				MREntityManager::GetInstance()->createEnemy(wave[waveIndex].enemy);
				timer.restart();
				++waveIndex;
			}

			break;
		case 2:
			myVehicle.update();
			MREntityManager::GetInstance()->update();
			if (timer.elapsed() > 7000){ result = MREntityManager::GetInstance()->getScore(); scene = 3; }
			break;
		case 3:
		{
			const Point rectSize(230, 100);

			Rect(Point(320-rectSize.x/2, 270), rectSize).draw(Palette::Black);
			FontAsset(L"Result").drawCenter(L"鬼退治成績", Point(320, 300), Palette::Red);
			FontAsset(L"Result").drawCenter(Format(result), Point(320, 340), Palette::Red);
		}
		break;
		default:
			break;
		}








	}
}
