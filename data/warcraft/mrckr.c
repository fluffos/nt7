// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m飞镖[2;37;0m[2;37;0m", ({"febiao"}));        
        set("gender", "女性");                
        set("long", "$HIB$飞镖[2;37;0m
它是慕容楚的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mrckr");
        set("owner_name", "慕容楚");
        set_temp("owner", "mrckr");
        set_temp("owner_name", "慕容楚");
        ::setup();
}
