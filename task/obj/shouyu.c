#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIG"方丈手谕"NOR,({ "shouyu" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "纸");
                set("material", "paper");
                set("long", "这是一张空白的方丈专用手谕笺。\n");
        }
        set("owner", "玄慈大师");
        setup();
}  
