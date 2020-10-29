// Room: xiangfang.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "厢房");
        set("long", @LONG
这是内室厢房，四周布置一望便知是小姐的闺房。石桌石凳，颇有山野气
息，房里乱挂了些书画，一望可知主人是没有什么修养的。窗外盛开着一些野
山茶花，不远处的山石提醒你这是在一个山谷里。
LONG
        );
        set("exits", ([            
            "west" : __DIR__"keting",
        ]));

        set("objects", ([
              __DIR__"npc/gan_baobao" : 1,
        ]));
        
        setup();
}