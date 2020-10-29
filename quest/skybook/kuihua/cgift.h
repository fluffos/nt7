// YUJ@SJ 2001-11-02
// Modified by LOOKLOVE@SJ 引入乘幂计算，大大优化。
// 2002/4/29
// 改为玩家自行修改属性

// Exp在 100K 以上可以修改属性。
#define MIN_EXP 100000
// 剩余EXP比率等于100%减去每点扣除比率
// 当前修改每点属性，扣除exp比率为5%
#define RATE 0.9500

#include <ansi.h>

int help();

nosave mapping gift_desc = ([
	"str":"膂力",
	"con":"根骨",
	"dex":"身法",
	"int":"悟性"
]);

nosave string *gift = keys(gift_desc);

// 统一过滤 by Lklv
string check(object me)
{
	string msg;

	if (me->query("registered") < 3)
		msg = "抱歉：只有贵宾玩家才有这个机会。\n";
	if ((int)me->query("combat_exp") < MIN_EXP)
		msg = "抱歉：你的经验不够 "+MIN_EXP+" ，无法修改属性。\n";
	if (me->is_ghost())
		msg = "抱歉：你的状态不稳定，现在无法修改属性。\n";
	return msg;
}

// yuj 新公式，利用循环算法。
int check_exp(int exp, int num)
{
        while (num--) exp -= exp / 20;
        return exp;
}

int do_change(string arg)
{
	string msg, from, to;
	int exp, num, newexp, tmpexp;
	object me = this_player();

	if (!me) return 0;
	if (!arg) return help();

	if ( stringp(msg = check(me)) )
		return notify_fail(msg);

	if (sscanf(arg, "%d %s to %s", num, from, to) == 3){
		if ( num < 1 || num > 20)
			return notify_fail("输入数字无效，请重新输入。\n");

		exp = me->query("combat_exp");
		newexp = check_exp(exp,num);
		tmpexp = exp - newexp;

		if (member_array(from, gift) < 0)
			return notify_fail("你要扣除什么天赋？\n");

		if (member_array(to, gift) < 0)
			return notify_fail("你要增加什么天赋？\n");

		if (from == to)
			return notify_fail("检查一下，输入错误，可能眼花。\n");

		if (me->query(from) <= 10)
			return notify_fail("你的"+gift_desc[from]+"不能再减少了。\n");

		if ( ((int)me->query(from) - num) < 10)
			return notify_fail("你的"+gift_desc[from]+"减少"+num+"点后将少于10点，不能修改。\n");

		if (me->query(to) >= 30 )
			return notify_fail("你的"+gift_desc[to]+"已经大于30点，不能再增加了。\n");

		if ( ((int)me->query(to) + num) > 30)
			return notify_fail("你的"+gift_desc[to]+"增加"+num+"点后将超过30点，不能修改。\n");

		if ( newexp < 95000 )
			return notify_fail("抱歉：修改"+num+"点属性后经验将不够 "+MIN_EXP+" ，建议你一次少修改几点属性。\n");

		switch (me->query("family/family_name")) {
			case "明教":
				if (from == "int" && ( me->query("int") <= 20 || ((int)me->query("int") - num) < 20 ) )
					return notify_fail("明教弟子悟性要求至少 20。\n");
				break;
			case "大轮寺":
				if (from == "str" && ( me->query("str") <= 20 || ((int)me->query("str") - num) < 20) )
					return notify_fail("大轮寺弟子膂力要求至少 20。\n");
				if (from == "con" && ( me->query("con") <= 20 || ((int)me->query("con") - num) < 20) )
					return notify_fail("大轮寺弟子根骨要求至少 20。\n");
				break;
		}

		if (! me->query("confirm_passwd"))
			return notify_fail("您没有设置确认密码(help passwd)，无法修改属性。\n");

		write(HIR"请输入确认密码：\n"NOR);
		input_to("confirm_passwd", me, from, to, num);
		return 1;
	}

	if (sscanf(arg, "check %d", num) == 1){
		if ( num < 1 || num > 80 )
			return notify_fail("输入的数值超过了你的隐藏属性合。\n");

		exp = me->query("combat_exp");
		newexp = check_exp(exp,num);
		tmpexp = exp - newexp;

		msg = HIG"提示：如果要修改 "+num+" 点属性，你大约要扣除 "+tmpexp+" 点EXP，还剩 "+newexp+" 点EXP。\n"NOR;

		if ( newexp < 95000 )
			msg += HIR"抱歉：修改"+num+"点属性后经验将不够 "+MIN_EXP+" ，建议你一次少修改几点属性。\n"NOR;

		if (me->query_skill("jinshe-zhangfa",1) || me->query_skill("jinshe-jianfa",1))
			msg += HIR"注意：如果修改臂力高于20，金蛇剑法和金蛇掌法将被删除。\n"NOR;

		if (me->query("double_attack") && me->query("zhou"))
			msg += HIR"注意：如果修改悟性高于25，左右互搏将被删除。\n"NOR;

		if (me->query("dali") && me->query_skill("lingbo-weibu", 1))
			msg += HIR"注意：如果修改悟性低于22，凌波微步将被删除。\n"NOR;

		if ( me->query("quest/qianzhu/pass") )
			msg += HIR"注意：如果修改根骨低于15或悟性低于20，千蛛万毒手将被删除。\n"NOR;

		if ( me->query("quest/pixie/pass") )
			msg += HIR"注意：如果修改身法低于15或悟性低于20，葵花神功将被删除。\n"NOR;

		if ( me->query("quest/ningxue/pass") )
			msg += HIR"注意：如果修改身法低于15或根骨低于15，凝血神爪将被删除。\n"NOR;

		write(msg);
		return 1;
	}
	return help();
}

private void confirm_passwd(string pass, object me, string from, string to, int num)
{
	int exp, newexp, tmpexp;
	string confirm_pass;
	confirm_pass = me->query("confirm_passwd");

	if ( confirm_pass && crypt(pass, confirm_pass) != confirm_pass) {
		write("确认密码错误！\n");
		return;
	}
	// 计算扣除exp
	exp = me->query("combat_exp", 1);
	newexp = check_exp(exp,num);
	tmpexp = exp - newexp;

	me->start_busy(1);

	me->add(from, -num);
	me->add(to, num);
	me->add("combat_exp", -tmpexp);

	// 膂力限制金蛇秘籍
	if ( me->query("str") > 20) {
		me->delete_skill("jinshe-zhangfa");
		me->delete_skill("jinshe-jianfa");
	}

	// 悟性限制读书写字
	if (me->query_skill("literate", 1) > me->query("int") * 10)
		me->set_skill("literate", me->query("int") * 10);

	// 双手互搏要求悟性 <= 25
	if (me->query("int") > 25 ){
		me->delete("double_attack");
		me->delete("zhou/hubo");
	}

	// 凌波微步要求悟性 >= 22
	if ( me->query("int") < 22 ){
		me->delete("dali/pass");
		me->delete("dali/meet_dy1");
		me->delete_skill("lingbo-weibu", 1);
	}

	// 千蛛万毒手要求悟性 >=20 且根骨 >=15
	if ( me->query("int") < 20 || me->query("con") < 15 ) {
		me->delete("quest/qianzhu/pass");
		me->delete_skill("qianzhu-wandushou", 1);
	}

	// 葵花神功要求悟性 >=20 且根骨 >=15
	if ( me->query("int") < 20 || me->query("dex") < 15 ) {
		me->delete("quest/pixie/pass");
		me->delete_skill("pixie-jian", 1);
		me->delete_skill("kuihua-shengong", 1);
	}

	// 凝血神爪要求根骨 >=15 且身法 >=15
	if ( me->query("dex") < 15 || me->query("con") < 15 ) {
		me->delete("quest/ningxue/pass");
		me->delete_skill("ningxue-shenzhua", 1);
	}

	me->setup();
	me->save();
	write(HIY"你将"+num+"点"+gift_desc[from]+"调整到"+gift_desc[to]+"上。\n"NOR, me);
	log_file("nosave/ADJUST",
		me->query("name")+"("+capitalize(geteuid(me))+")"
		+"调整"+num+"点"+gift_desc[from]
		+"到"+gift_desc[to]+"上，扣除 "+tmpexp+" 点经验，剩余"+newexp+"\n",
		me,
		({ me })
	);
	return;
}

int help()
{
	write(HIR"修改先天属性，每点属性修改将扣除 5% 经验值。\n"NOR);
	write("EXP不足"+MIN_EXP+"不能修改属性。\n");
	write("\n");
	write("指令格式：\n");
	write("    计算扣除损失：cgift check <要修改的点数>\n");
	write("    修改属性：cgift <点数> <要扣除的天赋> to <要增加的天赋>\n");
	write("\n");
	write("可使用的属性参数：\n");
	write("    膂力  str           根骨  con\n");
	write("    身法  dex           悟性  int\n");
	write("\n");
	write(HIR"请慎重使用，操作失误后果自负，改错不补。\n"NOR);
	return 1;
}
