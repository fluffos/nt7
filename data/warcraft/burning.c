// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m杀气[2;37;0m[1;32m腾[1;35m腾[2;37;0m[2;37;0m", ({"cruel"}));        
        set("gender", "男性");                
        set("long", "杀气腾腾[2;37;0m
它是火腾腾的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "burning");
        set("owner_name", "火腾腾");
        set_temp("owner", "burning");
        set_temp("owner_name", "火腾腾");
        ::setup();
}
