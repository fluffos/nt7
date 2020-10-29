// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火[1;33m雀雀[2;37;0m[2;37;0m", ({"gooo"}));        
        set("gender", "女性");                
        set("long", "$HIR$火$HIY$雀雀[2;37;0m
它是卓卓的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qiu");
        set("owner_name", "卓卓");
        set_temp("owner", "qiu");
        set_temp("owner_name", "卓卓");
        ::setup();
}
