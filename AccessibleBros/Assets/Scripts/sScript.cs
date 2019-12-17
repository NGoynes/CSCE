using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class sScript : MonoBehaviour
{
	// Start is called before the first frame update
	public bool subBool = false;
	public bool subOn = false;
	public GameObject textBox1;
	float timer = 0;

	// Update is called once per frame

	void Update()
	{
		timer += 1;
		subBool = Mario.jumpSub;
		subOn = MainMenu.SubsActive;
		Debug.Log("Hello: " + Mario.jumpSub);
		if (subBool == false && timer % 20 == 0)
		{
			textBox1.GetComponent<Text>().text = "";

			return;
		}
		if (subBool == true)
		{

			textBox1.GetComponent<Text>().text = "*jump*";

			Mario.jumpSub = false;
			return;
		}
		if (subOn == false)
		{
			textBox1.SetActive(false);
			
			return;
		}
		if (subOn == true)
		{
			textBox1.SetActive(true);
			
			return;
		}
		if (timer == 1000000)
		{
			timer = 0;

		}
	}
}
