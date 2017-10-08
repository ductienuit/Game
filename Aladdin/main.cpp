#include <windows.h>
#include <d3d9.h>
#include<d3dx9.h>
#include"AladdinGame.h"
#include"Engine.h"

using namespace std;
//OK
//m thấy cái ổ khóa ko, nó có nghĩa là chưa chỉnh sửa j trong đó
//Dấu tích màu đỏ, nghĩa là t vừa chỉnh sửa nó mà chưa up lên github
//Thao tác của m sau này là gì ?

//Sync
//Outgoing commit là code mà m code xong, nhấn change rồi commit nó. Nhưng nó mới chỉ là commit
//Chưa push lên github
//Incoming Commits là code của người trong nhóm đăng lên github, m chưa sync về máy

//Branch
//Branch nó rất khó, nhưng t sẽ chỉ sau cho. Khi code hai người đang thay đổi cấu trúc quá nhiều
//thì mới tạo Branch sau đó gộp n cái Branch này với nhau.

//master là nhánh branch chính.
//Ghi code trong này.
//Sau khi code xong, nhấn View->Team-> Change

//Nó hoạt động thế nào?
//Mỗi ngày của m sẽ thế nào ?
//Bật visual rồi nhấn nhấn View->Team-> Sync. Nhấn Fetch coi có thằng nào commit code ko
//Chú ý: Phải commit code của mình trước rồi mới có thể tải code về (Pull)
//Nếu có thì click vào coi thử đã rồi mới sync về
//Ví dụ cho coi: Coi kĩ.
//Bước 1: t vào Changes rồi commit code này.

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AladdinGame* myGame = new AladdinGame(hInstance, "ALADDIN");
	myGame->InIt();
	myGame->Run();
	myGame->Release();
	delete myGame;
	system("pause");
	return 1;
}