// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m铃木[5m[1;37m盗匪[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这是铃木公司最新款街头跑车，不时发出轰鸣声，泡妞利器[2;37;0m
它是流川枫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "balll");
        set("owner_name", "流川枫");
        set_temp("owner", "balll");
        set_temp("owner_name", "流川枫");
        ::setup();
}
