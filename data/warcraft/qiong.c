// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m乌云[5m[1;37m盖雪[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹神驹通体雪白，马背黑色如云，追风逐电、神骏非凡。[2;37;0m
它是秦琼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qiong");
        set("owner_name", "秦琼");
        set_temp("owner", "qiong");
        set_temp("owner_name", "秦琼");
        ::setup();
}
