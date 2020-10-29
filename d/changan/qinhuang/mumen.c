// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "秦皇陵");
        set("long", @LONG
走出墓穴，眼前豁然开朗，在这浩大的地下宫殿里，却一点都不
觉得和地面有什么区别，顶上镶嵌着无数散发着荧光的『星星』，足
以让你看清四周的景象了。
LONG );
    set("exits", ([
       "east" :__DIR__"shendao",
]));
    setup();
    replace_program(ROOM);
}