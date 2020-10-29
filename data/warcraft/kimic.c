// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火凤凰[2;37;0m[2;37;0m", ({"phx"}));        
        set("gender", "女性");                
        set("long", "这是kimic的坐骑[2;37;0m
它是东邪西毒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kimic");
        set("owner_name", "东邪西毒");
        set_temp("owner", "kimic");
        set_temp("owner_name", "东邪西毒");
        ::setup();
}
