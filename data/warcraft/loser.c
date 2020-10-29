// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m神白虎[2;37;0m[2;37;0m", ({"nicole"}));        
        set("gender", "女性");                
        set("long", "一只老虎，跑的快，跑的快[2;37;0m
它是蛇蛇鲁的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "loser");
        set("owner_name", "蛇蛇鲁");
        set_temp("owner", "loser");
        set_temp("owner_name", "蛇蛇鲁");
        ::setup();
}
