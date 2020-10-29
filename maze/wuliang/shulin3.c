// shulin3.c
// Modify By River 98/12
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "山中密林");
	set("long", @LONG
仰望高崖，白雾封谷，谷中静悄悄的，别说人迹，就连兽踪也无半点，唯
闻鸟语相间，遥相和呼，逆着瀑布从下往上看去，只见瀑布之右一块石壁光润
如玉，不知多少年的冲激磨洗，才将这半面石壁磨得如此平整，后来瀑水量减
少，才将这片如琉璃，如明镜的石壁露了出来。
LONG
	);
        set("exits", ([
	    "south" : __DIR__"nanhubian",
        ]));
 
	set("objects", ([
	   __DIR__"obj/yeguo" : 2,
	]));
        set("outdoors", "大理"); 
	setup();
}
