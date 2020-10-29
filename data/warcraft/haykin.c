// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎虎[2;37;0m[2;37;0m", ({"huhu"}));        
        set("gender", "男性");                
        set("long", "一只朱雀[2;37;0m
它是贺诚的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "haykin");
        set("owner_name", "贺诚");
        set_temp("owner", "haykin");
        set_temp("owner_name", "贺诚");
        ::setup();
}
