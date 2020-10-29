inherit ROOM;

void create()
{
        set("short", "厢房");
        set("long", @LONG
这是一间布置精美的房间，正中是一长红木八仙桌，左手一
个大书架几乎占了一面墙，仔细看上面全是医学经脉类的典籍，
居然没有一本武功书籍。
LONG
        );
        set("exits", ([
  "south" : __DIR__"yitong",
]));

        setup();
        replace_program(ROOM);
}
