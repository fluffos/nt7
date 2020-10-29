// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m凤凰[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "女性");                
        set("long", "一只美丽的凤凰[2;37;0m
它是纳兰潇潇的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "nlxx");
        set("owner_name", "纳兰潇潇");
        set_temp("owner", "nlxx");
        set_temp("owner_name", "纳兰潇潇");
        ::setup();
}
