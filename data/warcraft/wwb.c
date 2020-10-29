// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m本体[1;31m二呜[2;37;0m[2;37;0m", ({"wwbb"}));        
        set("gender", "女性");                
        set("long", "呜呜[2;37;0m
它是二呜呜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wwb");
        set("owner_name", "二呜呜");
        set_temp("owner", "wwb");
        set_temp("owner_name", "二呜呜");
        ::setup();
}
