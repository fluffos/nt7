// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "七夕台");
        set("long", @LONG
圆缘台东，又是一座平台，镌有一碑，题名『七夕』。七夕台修
葺得相当整齐洁净，面悬崖的一边拦了一排汉白玉石阑干。凭阑远眺，
雾霭溟蒙，白云荡漾。每到星夜，在七夕台观到的牛郎织女星总是分
外明亮。千种缠绵、万般恩爱浓得似乎能够传到人间。难怪词人云：
纤云弄巧，飞星传恨，银汉迢迢暗度。金风玉露一相逢，便胜却、人
间无数；柔情似水，佳期如梦，忍顾鹊桥归路。两情若是久长时，又
岂在、朝朝暮暮。　
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/sansheng-shi",
                "west" : "/d/hangzhou/yuanyuan-tai",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 780);
	set("coor/y", -1970);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}