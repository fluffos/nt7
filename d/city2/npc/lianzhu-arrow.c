inherit SKILL;

int valid_enable(string usage) { return  usage=="arrow"; }
int valid_learn(object me)
{
  return notify_fail("连珠箭法只能向郭靖请教(qingjiao)来学习！\n");    
}

string perform_action_file(string action)
{
        return __DIR__"lianzhu-arrow/" + action;
}                 