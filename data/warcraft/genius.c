// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m冰焰凤凰[2;37;0m[2;37;0m", ({"phoenix"}));        
        set("gender", "女性");                
        set("long", "沐浴在寒冰火焰中的凤凰神兽。[2;37;0m
它是雪舞聆风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "genius");
        set("owner_name", "雪舞聆风");
        set_temp("owner", "genius");
        set_temp("owner_name", "雪舞聆风");
        ::setup();
}
