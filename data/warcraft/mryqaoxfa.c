// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是高淑宏的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mryqaoxfa");
        set("owner_name", "高淑宏");
        set_temp("owner", "mryqaoxfa");
        set_temp("owner_name", "高淑宏");
        ::setup();
}
