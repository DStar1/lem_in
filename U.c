void		dkstra(t_mast *mast)
{
	// t_links *mast->tmp;

	// mast->weight = 0;
	// mast->cnt = 0;
	// mast->cnt1 = 0;
	while (mast->que[mast->weight][0] != mast->end)
	{
		mast->tmp = mast->hash_arr[mast->que[mast->weight][0]];
		(mast->cnt == 0) ? mast->cnt++ : 0;
		mast->weight++;
		if (mast->weight >= mast->rooms)
			ERROR("There's no path\n");
		while(mast->tmp != NULL)
		{
			mast->cnt1 = 0;
			int i = 0;
			for (i = 0; i <= mast->cnt && i < mast->rooms; i++)
				if ((mast->que[i][0] == mast->tmp->l2_id) && mast->que[i][2] != 0 && mast->que[i][2] <= mast->weight)
					mast->cnt1++;
			if (mast->cnt1 == 0)
			{
				mast->que[mast->cnt][0] = mast->tmp->l2_id;
				mast->que[mast->cnt][1] = mast->tmp->l1_id;
				mast->que[mast->cnt][2] = mast->weight;				
				if (mast->que[mast->cnt][0] == mast->end)
				{
					mast->weight = mast->cnt;
					construct(mast);
					return ;
				}
				mast->cnt++;
			}
			mast->tmp = mast->tmp->next;
		}
	}
}