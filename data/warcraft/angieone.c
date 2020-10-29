// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("安妮[2;37;0m[2;37;0m", ({"annie"}));        
        set("gender", "男性");                
        set("long", "快乐的小安妮[2;37;0m
它是慕容小二的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "angieone");
        set("owner_name", "慕容小二");
        set_temp("owner", "angieone");
        set_temp("owner_name", "慕容小二");
        ::setup();
}
