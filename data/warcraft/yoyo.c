// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m灵魂[1;37m坐骑[2;37;0m[2;37;0m", ({"yoku"}));        
        set("gender", "男性");                
        set("long", "一匹来自远古....[2;37;0m
它是杨逍遥的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yoyo");
        set("owner_name", "杨逍遥");
        set_temp("owner", "yoyo");
        set_temp("owner_name", "杨逍遥");
        ::setup();
}
