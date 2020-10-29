// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m田青[2;37;0m[2;37;0m", ({"cyana"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是田清的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cyan");
        set("owner_name", "田清");
        set_temp("owner", "cyan");
        set_temp("owner_name", "田清");
        ::setup();
}
