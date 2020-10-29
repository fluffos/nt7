// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m丰田[2;37;0m[2;37;0m", ({"civic"}));        
        set("gender", "女性");                
        set("long", "this is honor civic[2;37;0m
它是慕容安娜的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "leona");
        set("owner_name", "慕容安娜");
        set_temp("owner", "leona");
        set_temp("owner_name", "慕容安娜");
        ::setup();
}
