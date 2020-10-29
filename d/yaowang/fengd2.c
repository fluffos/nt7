
inherit __DIR__"fengd";

void create()
{
        set("short", "灌木丛");
        set("long", query_long());
        set("exits", ([
        "west" : __DIR__"fengd3",
        "east" : __DIR__"fengd1",
        "north" : __DIR__"fengd5",
]));

        set("item_desc", ([
        "果子" : (: query_item_desc :),
        "小果子" : (: query_item_desc :),
]));
        set("outdoors", "yaowang");
        setup();
}
