#include <ansi.h>
inherit TASK;
void create()
{
    set_name( CYN "帐本" NOR, ({ "zhang ben" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本厚厚的账本，里面密密麻麻的记录着一大堆帐目。\n");
          }
    set("owner", "杨永福");
    setup();
}
