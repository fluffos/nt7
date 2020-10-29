// By haiyan

inherit ROOM;

int is_chat_room() {return 1;}
void create()
{
        set("short", "茶室");
        set("long", @LONG
这里是春来茶馆的二楼雅座。你站在楼上眺望，只见扬州大街上
人群熙攘，小贩子的叫卖声掺杂着讨价声此起彼伏。许多穿着考究的
公子哥儿频繁进出于对面一间装饰华丽的大院，不时传来阵阵打情骂
俏的声音。江湖上许多事都可以在这里打听到。
LONG );

        set("exits", ([
                "down" : "/d/city/chaguan",
        ]));

        set("no_fight", "1");
        setup();
        "/clone/board/player_b"->foo();
}
