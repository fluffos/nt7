#include <ansi.h>
inherit TASK;
void create()
{
    set_name(CYN"唐家家谱"NOR, ({ "jiapu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "一张唐家家谱\n");
          }
    set("owner", "唐楠");
    setup();
}
