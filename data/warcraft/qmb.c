// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m幽冥魔兽[2;37;0m[2;37;0m", ({"qmbb"}));        
        set("gender", "男性");                
        set("long", "幽冥魔兽[2;37;0m
它是武当医生的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qmb");
        set("owner_name", "武当医生");
        set_temp("owner", "qmb");
        set_temp("owner_name", "武当医生");
        ::setup();
}
