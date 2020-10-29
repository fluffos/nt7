// jidao-shaqi.c 极道煞气
// By Alf

inherit FORCE;

int valid_enable(string usage)
{
    return usage == "force";
}

int valid_learn(object me)
{
    int lvl = (int)me->query_skill("jidao-shaqi", 1);

    if ((int)me->query_skill("force", 1) < 30)
        return notify_fail("你的基本内功火候还不够，还不能学习极道煞气。\n");

    if (
    me->query_skill("bahuang-gong",1)    // 灵鹫：八荒六合功
    || me->query_skill("beiming-shengong",1)    // 逍遥：北冥神功
    || me->query_skill("bibo-shengong",1)    // 桃花：碧波神功
    || me->query_skill("chunyang-gong",1)    // 大理：纯阳功
    || me->query_skill("hamagong",1)    // 白驼：蛤蟆功
    || me->query_skill("huagong-dafa",1)    // 星宿：化功大法
    || me->query_skill("huntian-qigong",1)    // 丐帮：混天气功
    || me->query_skill("hunyuan-yiqi",1)    // 少林：混元一气功
    || me->query_skill("jiuyang-shengong",1)    // 少林：九阳神功
    || me->query_skill("linji-zhuang",1)    // 峨嵋：临济十二庄
    || me->query_skill("longhu-baqi",1)    // 武官：龙虎霸气
    || me->query_skill("nilian-shengong",1)    // 白驼：逆练神功
    || me->query_skill("shenlong-zhanqi",1)    // 神龙：神龙战气
    || me->query_skill("taiji-shengong",1)    // 武当：太极神功
    || me->query_skill("wolong-xingfa",1)    // 巡捕：卧龙心法
    || me->query_skill("wuwang-shenzhou",1)    // 凌霄城：无妄神咒
    || me->query_skill("xiantian-gong",1)    // 全真：先天功
    || me->query_skill("xiawuxiang",1)    // 雪山：小无相功
    || me->query_skill("xuanmen-neigong",1)    // 全真：玄门内功
    || me->query_skill("yunlong-shengong",1) // 云龙：云龙神功
    || me->query_skill("zixia-shengong",1) )    // 华山：紫霞神功
        return notify_fail("你不先散了别派内功，怎能学极道煞气？！\n");
    return 1;
}


int practice_skill(object me)
{
    return notify_fail("极道煞气只能通过学习(xue)，或是从运用(yun)中增加熟练度。\n");
}

string exert_function_file(string func)
{
    return "/kungfu/perform/jidao-shaqi/" + func;
}

