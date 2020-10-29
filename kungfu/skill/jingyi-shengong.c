// 

inherit SKILL;

int valid_learn(object me)
{
        return notify_fail("精意神功是你对万物方面的领悟，无法"
                           "通过简单学习获得提升。\n");
}

int valid_research(object me)
{
        return notify_fail("精意神功来自你在精意山庄对万物领会的吸"
                           "收，无法通过研究提升。\n");
}