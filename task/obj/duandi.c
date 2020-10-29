#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"白玉短笛"NOR, ({ "duan di", "di",}));
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "只");
            set("material", "stone");
            set("long", WHT"这玉笛短得出奇，只不来七寸来长、通体洁白，晶莹可爱。\n" NOR);
          }
    set("owner", "采花子");
    setup();
}
