using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SubScript : MonoBehaviour
{
	public GameObject textBox;
	public bool tipBool = true;
	public bool isComplete = false;
	MainMenu menu;
	int t1 = 1;
	int t2 = 5;
	void Start()
	{
		StartCoroutine(TipLibrary());

	}
	IEnumerator TipLibrary()
	{

		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Change the music and sound volume on the main screen";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Try speaking louder to jump higher";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Try pressing the down key over a pipe";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: You win the game by winning";
		yield return new WaitForSeconds(t2); 
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Do not touch the Goombas";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: You can turn these off on the main screen";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Press C for auto run";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Press down arrow to crouch";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Press M for a different game speed";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Try hitting the ? boxes for coins or powerups";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		//isComplete = true;
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Press V to toggle voice jump";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(t1);
		textBox.GetComponent<Text>().text = "Pro Tip: Try Sandbox mode for practice!";
		yield return new WaitForSeconds(t2);
		textBox.GetComponent<Text>().text = "";
		yield return new WaitForSeconds(3);

	}

	void Update()
	{
		tipBool = MainMenu.tipsActive;
		Debug.Log("Hello: " + MainMenu.tipsActive);
		if (tipBool == false)
		{
			textBox.SetActive(false);
			//tipBool = true;
			return;
		}
		if (tipBool == true)
		{
			textBox.SetActive(true);
			//tipBool = false;
			return;
		}

		if (isComplete == true)
		{
			Debug.Log("Reaches here " + MainMenu.tipsActive);
			isComplete = false;
			StartCoroutine(TipLibrary());

		}

	}
	
}
