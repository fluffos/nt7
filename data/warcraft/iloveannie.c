// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("安琪[2;37;0m[2;37;0m", ({"angie"}));        
        set("gender", "男性");                
        set("long", "快乐的小安琪[2;37;0m
它是慕容惜花的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "iloveannie");
        set("owner_name", "慕容惜花");
        set_temp("owner", "iloveannie");
        set_temp("owner_name", "慕容惜花");
        ::setup();
}
