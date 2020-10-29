// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火凤凰[2;37;0m[2;37;0m", ({"huofenghuang"}));        
        set("gender", "女性");                
        set("long", "一只火凤凰，正凤翔九天之上。[2;37;0m
它是稍微丝袜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "celiou");
        set("owner_name", "稍微丝袜");
        set_temp("owner", "celiou");
        set_temp("owner_name", "稍微丝袜");
        ::setup();
}
