// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "大堤");
        set("long", @LONG
这里是一个大堤。旁边就是汹涌的大海，阵阵大风吹来，海浪拍打
着堤岸，溅得你身上都是海水。北边就是高丽的飞凤门了。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast" : __DIR__"qinglongmen",
                "southwest":__DIR__"dadi2",
        ]));
       setup();
        
}
