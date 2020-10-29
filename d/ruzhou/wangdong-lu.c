//Room: /d/ruzhou/wangxi-lu.c
// llm /99/07/

inherit ROOM;

void create()
{
        set("short", "望西路");
        set("long", @LONG
望西路上望西归，自此出汝州的西城门，便是踏上西去汉中，远
征西北的大路了。北面就是汝州城的知府衙门，虽然未经什么修缮，
但是略略掉漆的红木白墙却显现出一番更加威严肃穆的感觉。东去是
汝州城中心，这里也没有什么店铺。
LONG
        );

        set("exits", ([
      "north" : __DIR__"yamen-damen",
                "south" : __DIR__"yingbin-lou1",
                "west" : __DIR__"ximen",
                "east" : __DIR__"ruzhou",
        ]));

        set("objects", ([
        ]));

        set("outdoors", "ruzhou");
        setup();
        replace_program(ROOM);
}


