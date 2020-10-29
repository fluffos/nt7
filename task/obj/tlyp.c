#include <ansi.h>
inherit TASK;
void create()
{
    set_name(YEL"统领腰牌"NOR, ({ "tongling yaopai", "yao pai", "pai"}));
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "面");
            set("material", "iron");
            set("long", "这是一面满清帝国的御林军统领腰牌。\n");
          }
    set("owner", "多隆");
    setup();
}
