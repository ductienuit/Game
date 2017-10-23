#ifndef __GAMETIME_H__
#define __GAMETIME_H__
/* Tại sao có class này ?
   Hiển thị một hình sprite động chính xác
   Để tạo một hoạt cảnh có thể chuyển động mượt mà thì ứng dụng game của bạn phải là
ứng dụng là ứng dụng được quyền ưu tiên nhất trên hệ thống. Bằng cách sử dụng các
timer, các hoạt cảnh chuyển động có thể được xác lập để xuất hiện tại những thời điểm
xác định. Ví dụ, nếu bạn muốn chạy hoạt cảnh với tốc độ 30 khung hình trong một giây
(fps) nhưng tốc độ khung hình hiện tại ứng dụng game của bạn lại là 60 fps, bạn muốn
giảm tốc độ cập nhật của hoạt cảnh xuống nhằm tránh khả năng nó sẽ chạy hai lần. Trong
trường hợp này, bạn sẽ sử dụng một timer để quản lý quá trình cập nhật của hoạt cảnh
chậm hơn một nửa so với bình thường, kết quả bạn sẽ có tốc độ cập nhật là 30 fps.
  Có hai hàm hổ trợ là GetTickCount và QueryPerformanceCounter
  GetTickCount chỉ đếm được millisecond
  QueryPerformanceCounter thì microsecond, biểu diễn hoạt cảnh chính xác hơn.
  Ebook trang 59.
  Nói nhiều tụi m mệt quá.
*/
#include "define.h"
#include "TimeSpan.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN
//Khởi tạo Singleton static Gametime 
class GameTime
{
public:
	~GameTime(void);
	static void      Release();
	static GameTime* getInstance();
	void			 InIt();
	void			 ResetLastTick();
	void			 UpdateGameTime();
	float			 getElapsedGameTime();		// Tổng thời gian trôi qua kể từ lần cuối gọi update
	float			 getTotalGameTime();		// Tổng thời gian trôi qua kể từ lúc gọi Init
private:
	static GameTime* _instance;                  // static singleton
	TimeSpan		 _elapsedGameTime;           // Tổng thời gian trôi qua kể từ lần cuối gọi update
	TimeSpan		 _totalGameTime;             // Tổng thời gian trôi qua kể từ lúc gọi Init
	LARGE_INTEGER	 _Query;                     // Lấy thời gian từ phần cứng

	//Giá trị tần số của bộ đếm thời gian
	//Dựa vào đây chia tỷ lệ thời gian
	//hiển thị sprite để không lag
	float		     _freQuery;                   

	LONGLONG		 lastTicks;                   //thời gian kết thúc 1 vòng lặp trước đó, đc khởi tạo.
	LONGLONG		 curTicks;                    //thời gian sau khi kết thúc vòng lặp

	GameTime(TimeSpan& elapsedGameTime);
	GameTime(void);

	void setElapsedGameTime(TimeSpan& elapsedGt);
	void setTotalGameTime(TimeSpan& totalGt);
};
typedef GameTime *pGameTime;
GAME_FRAMEWORK_END
#endif  !__GAMETIME_H__
