using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Tutorial : MonoBehaviour
{
    public GameObject textBox;
    public bool showTutorial = true;

    // Start is called before the first frame update
    void Start()
    { 
        textBox.SetActive(showTutorial);
    }


    IEnumerator CheckForTutorial()
    {
        yield return new WaitForSeconds(1);

    }
    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.T))
        {
            Debug.Log("T pressed");
            showTutorial = !showTutorial;
            textBox.SetActive(showTutorial);
        }
        
    }
}
