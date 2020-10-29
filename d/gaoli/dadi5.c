// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "大堤");
        set("long", @LONG
这里是一个大堤。旁边就是汹涌的大海，阵阵大风吹来，海浪拍打
着堤岸，溅得你身上都是海水。这里的行人比较多，看来都是来这里乘
船的。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northwest" : __DIR__"dadi4",
                "southeast":__DIR__"dadi6",
        ]));
       setup();
        
}
