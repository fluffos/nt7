// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m睡袋[2;37;0m[2;37;0m[2;37;0m", ({"uptime"}));        
        set("gender", "女性");                
        set("long", "啊[2;37;0m
它是逍遥妃子的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "meccb");
        set("owner_name", "逍遥妃子");
        set_temp("owner", "meccb");
        set_temp("owner_name", "逍遥妃子");
        ::setup();
}
