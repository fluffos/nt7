#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "马厩");
        set("long", @LONG
这里是长安城的马厩，常年供应新鲜草料。长安民众富裕来往商
贾甚多，因此马夫们对马好生照看，将它们喂饱饮足再洗刷得干乾净
净，一直伺候到客人上路。马厩雨檐下的烂木柱上钉着块破木牌 (pa
izi)。马厩中堆放著几堆草料。
LONG );
        set("outdoors", "changan");
        set("no_fight", 1);
        set("no_beg", 1);
        set("no_clean_up", 0);
        set("resource/water", 1);        

        set("objects", ([
                "/clone/horse/zaohongma" : 1,
                "/clone/horse/huangbiaoma" : 1,
                "/clone/horse/ziliuma" : 1,
                "/clone/npc/mafu" : 1,
        ]));

        set("exits",([
                "south" : __DIR__"huarui1",
                "up"    : "/clone/shop/changan_shop",
               "north" : __DIR__"business",
        ]));
        set("coor/x", -10750);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}