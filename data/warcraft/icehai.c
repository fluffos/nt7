// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m冰凤凰[2;37;0m[2;37;0m", ({"ices"}));        
        set("gender", "女性");                
        set("long", "冰凤凰[2;37;0m
它是冰灵心的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "icehai");
        set("owner_name", "冰灵心");
        set_temp("owner", "icehai");
        set_temp("owner_name", "冰灵心");
        ::setup();
}
