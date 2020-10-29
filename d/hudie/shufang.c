// 书房 shufang.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "书房");
        set("long", @LONG
这里是胡青牛的书房，靠墙边有个大书柜，一排一排的书架上分
门别类地摆放着各种各样的医学书籍，连失传已久的《黄帝虾嫫经》、
《西方子明堂灸经》、《太平圣惠方》、《灸甲乙经》、《千金方》、
《此事难知》也在其中，书柜正对着一个书桌，上面摆放着一个笔筒，
笔筒旁边搁着一本打开的书。
LONG );

        set("exits", ([
            "west" : __DIR__"xfang3",
        ]));

        setup();
}