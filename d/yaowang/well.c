inherit ROOM;

void create()
{
        set("short", "水井");
        set("long", @LONG
这里是一片青青的草地，边上稀稀落落的长着几根青竹，草
地中央有一口井，井边的辘轳上挂着一只打水(fill)的木桶，奇
怪的是井台的的石头上不知道被谁弄成了红蓝相间的颜色。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");

        set("resource", ([
        "water" : 1,            // 打水标记
        "condition" : "scorpion_poison",   // 水中有毒

        "count" : 12,           // 毒发时间
        "time" : -1,            // 水中毒的有效时间，-1 代表永远有效
]));

        setup();
        replace_program(ROOM);
}
