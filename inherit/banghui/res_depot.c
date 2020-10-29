// res_ku.c
// 原料仓库
// by Find.

#define MAX_AMOUNT_PER_RES_IN_DEPOT	1000000000

/*
protected int depot_number = 1;
protected mixed *all_depots = ({});
*/

protected mapping res_depot = ([]);

protected int do_save_res_to_depot(string, int);

/*
protected void add_depot_number()
{
	if(depot_number <= 0)
		depot_number = 1;

	depot_number++;
}
*/

int save_res_to_depot(object ob)
{
	string res;
	int n;

	if(!objectp(ob)
	|| !ob->is_iron_class_res()
	|| !(res = ob->query_mine_class())
	|| !MINE_D->is_valid_mclass(res))
		return 0;

	if(!n = ob->query_sum())
	{
		n = ob->query_weight()/100;
		if(!n)
			return 0;
	}

	return (do_save_res_to_depot(res, n) > 0);
}

protected int do_save_res_to_depot(string res, int num)
{
	string up_res;
	int ps, up_num;

	if(!intp(num) || (num <= 0) || !MINE_D->is_valid_mclass(res))
		return 0;

	if(!mapp(res_depot))
		res_depot = ([]);

	if(!undefinedp(res_depot[res]))
	{
		if(res_depot[res] >= MAX_AMOUNT_PER_RES_IN_DEPOT)
			return 0;
		ps = num + res_depot[res];
	}
	else
		ps = num;

	if(ps > MAX_AMOUNT_PER_RES_IN_DEPOT)
		return 0;

	if( (up_res = MINE_D->query_mine_class_up_class(res))
	&& (ps >= (up_num = MINE_D->query_mine_class_up_quantity(res))) )
	{
		int rnt;

		if( (rnt = do_save_res_to_depot(up_res, ps/up_num)) == 1 )
		{
			if(!(ps %= up_num))
				return 1;
		}
		else if(rnt < 0)
			ps = abs(rnt)*up_num + ps%100;
	}

	if(undefinedp(res_depot[res]))
		res_depot += ([ res : ps ]);
	else
	{
		if(ps > MAX_AMOUNT_PER_RES_IN_DEPOT)
		{
			res_depot[res] = MAX_AMOUNT_PER_RES_IN_DEPOT;
			return -(ps - MAX_AMOUNT_PER_RES_IN_DEPOT);
		}

		else
			res_depot[res] = ps;
	}

	return 1;
}
