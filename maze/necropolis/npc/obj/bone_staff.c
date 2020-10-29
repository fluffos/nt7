 // staff.c
#include <weapon.h>
inherit STAFF; 
void create() {
        set_name("骨杖", ({ "bone staff" }) );
        set_weight(2000);
        set("maze_item",1); 
        set("no_put",1);
        /*if(clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", "这是一根不知道什么的骨头做成的法杖。");
                set("value", 300);
                set("material", "wood");
                set("wield_msg", "$N把$n紧紧地握在手中。\n");
                set("unwield_msg", "$N松开了手中的$n。\n");
        }
        ::init_staff(30);
}