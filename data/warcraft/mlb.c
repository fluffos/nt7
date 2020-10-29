// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("好大的蛋啊[2;37;0m[2;37;0m", ({"egg"}));        
        set("gender", "女性");                
        set("long", "$HIY$[2;37;0m
它是荷包鸡蛋的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mlb");
        set("owner_name", "荷包鸡蛋");
        set_temp("owner", "mlb");
        set_temp("owner_name", "荷包鸡蛋");
        ::setup();
}
