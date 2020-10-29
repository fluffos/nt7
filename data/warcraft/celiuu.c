// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青凤[2;37;0m[2;37;0m", ({"jiuwei"}));        
        set("gender", "女性");                
        set("long", "look[2;37;0m
它是慕容小白的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "celiuu");
        set("owner_name", "慕容小白");
        set_temp("owner", "celiuu");
        set_temp("owner_name", "慕容小白");
        ::setup();
}
