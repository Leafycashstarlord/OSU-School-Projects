<?php
session_start();

// Include config file
require_once "config.php";
$Ssn = $_SESSION["Ssn"]; 

// Define variables and initialize with empty values
$Dname = $Bdate = $Sex = $Relationship = "";
$Dname_err = $Birth_err = $Sex_err = $Relationship_err = "" ;
 
// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
    // Validate name
    $Dname = trim($_POST["Dname"]);
    if(empty($Dname)){
        $Dname_err = "Please enter a Dname.";
    } elseif(!filter_var($Dname, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"/^[a-zA-Z\s]+$/")))){
        $Dname_err = "Please enter a valid dependent.";
    } 
    // Validate Relationship
    $Relationship = trim($_POST["Relationship"]);
    if(empty($Relationship)){
        $Relationship_err = "Please enter a Relationship.";
    } elseif(!filter_var($Relationship, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"/^[a-zA-Z\s]+$/")))){
        $Relationship_err = "Please enter a valid Relationship.";
    } 
	// Validate Sex
    $Sex = trim($_POST["Sex"]);
    if(empty($Sex)){
        $Sex_err = "Please enter Sex.";     
    }
	// Validate Birthdate
    $Bdate = trim($_POST["Bdate"]);

    if(empty($Bdate)){
        $SBdate_err = "Please enter birthdate.";     
    }	

    // Check input errors before inserting in database
    if(empty($Relationship_err) && empty($Dname_err) && empty($Birth_err) && empty($Sex_err)){
        // Prepare an insert statement
        $sql = "INSERT INTO DEPENDENT (Essn, Dependent_name, Relationship, Sex, Bdate) 
		        VALUES (?, ?, ?, ?, ?)";
         
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "issss", $param_Essn, $param_Dname, $Relationship, 
				$param_Sex, $param_Bdate);
            
            // Set parameters
			$param_Essn = $Ssn;
            $param_Dname = $Dname;
			$param_Relationship = $Relationship;
			$param_Sex = $Sex;
			$param_Bdate = $Bdate;
            
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records created successfully. Redirect to landing page
				    header("location: index.php");
					exit();
            } else{
                echo "<center><h4>Error while creating new dependent</h4></center>";
				$Ssn_err = "Something went wrong";
            }
        }
         
        // Close statement
        mysqli_stmt_close($stmt);
    }

    // Close connection
    mysqli_close($link);
}
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Create Record</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <style type="text/css">
        .wrapper{
            width: 500px;
            margin: 0 auto;
        }
    </style>
</head>
<body>
    <div class="wrapper">
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-12">
                    <div class="page-header">
                        <h2>Create Record for Dependent <?php $Ssn ?></h2>
                    </div>
                    <p>Please fill this form and submit to add an Employee record to the database.</p>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                 
						<div class="form-group <?php echo (!empty($Dname_err)) ? 'has-error' : ''; ?>">
                            <label>Dependents Name</label>
                            <input type="text" name="Dname" class="form-control" value="<?php echo $Dname; ?>">
                            <span class="help-block"><?php echo $Dname_err;?></span>
                        </div>
						<div class="form-group <?php echo (!empty($Relationship_err)) ? 'has-error' : ''; ?>">
                            <label>Relationship</label>
                            <input type="text" name="Relationship" class="form-control" value="<?php echo $Relationship; ?>">
                            <span class="help-block"><?php echo $Relationship_err;?></span>
                        </div>
						<div class="form-group <?php echo (!empty($Sex_err)) ? 'has-error' : ''; ?>">
                            <label>Sex</label>
                            <input type="text" name="Sex" class="form-control" value="<?php echo $Sex; ?>">
                            <span class="help-block"><?php echo $Sex_err;?></span>
                        </div>              
						<div class="form-group <?php echo (!empty($Birth_err)) ? 'has-error' : ''; ?>">
                            <label>Birth date</label>
                            <input type="date" name="Bdate" class="form-control" value="<?php echo date('Y-m-d'); ?>">
                            <span class="help-block"><?php echo $Birth_err;?></span>
                        </div>

                        <input type="submit" class="btn btn-primary" value="Submit">
                        <a href="index.php" class="btn btn-default">Cancel</a>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>