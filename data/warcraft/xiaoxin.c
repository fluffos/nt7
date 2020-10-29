// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火[1;35m凤[1;36m凰[2;37;0m[2;37;0m", ({"xiaoxiao"}));        
        set("gender", "女性");                
        set("long", "一只[2;37;0m
它是良辰美景的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiaoxin");
        set("owner_name", "良辰美景");
        set_temp("owner", "xiaoxin");
        set_temp("owner_name", "良辰美景");
        ::setup();
}
